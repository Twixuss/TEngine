#include "sound.h"
#include "console.h"
#include "FileReader.h"
namespace TEngine {
   IDirectSound8* m_DirectSound;
   IDirectSoundBuffer* m_primaryBuffer;
   void Audio::Release() {
      if (m_primaryBuffer) {
         m_primaryBuffer->Release();
         m_primaryBuffer = nullptr;
      }
      if (m_DirectSound) {
         m_DirectSound->Release();
         m_DirectSound = nullptr;
      }
      TE_WARN("~~~ Audio released");
   }
   void AudioPlayer::Init() {
      DSBUFFERDESC bufferDesc;
      WAVEFORMATEX waveFormat;


      // Initialize the direct sound interface pointer for the default sound device.
      TE_HANDLE_HRESULT(DirectSoundCreate8(NULL, &m_DirectSound, NULL));

      // Set the cooperative level to priority so the format of the primary sound buffer can be modified.
      TE_HANDLE_HRESULT(m_DirectSound->SetCooperativeLevel(Window::hWnd, DSSCL_PRIORITY));

      //We have to setup the description of how we want to access the primary buffer.The dwFlags are the important part of this structure.In this case we just want to setup a primary buffer description with the capability of adjusting its volume.There are other capabilities you can grab but we are keeping it simple for now.

         // Setup the primary buffer description.
      bufferDesc.dwSize = sizeof(DSBUFFERDESC);
      bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
      bufferDesc.dwBufferBytes = 0;
      bufferDesc.dwReserved = 0;
      bufferDesc.lpwfxFormat = NULL;
      bufferDesc.guid3DAlgorithm = GUID_NULL;

      // Get control of the primary sound buffer on the default sound device.
      TE_HANDLE_HRESULT(m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL));

      //Now that we have control of the primary buffer on the default sound device we want to change its format to our desired audio file format.Here I have decided we want high quality sound so we will set it to uncompressed CD audio quality.

         // Setup the format of the primary sound bufffer.
         // In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
      waveFormat.wFormatTag = WAVE_FORMAT_PCM;
      waveFormat.nSamplesPerSec = 44100;
      waveFormat.wBitsPerSample = 16;
      waveFormat.nChannels = 2;
      waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
      waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
      waveFormat.cbSize = 0;

      // Set the primary buffer to be the wave format specified.
      TE_HANDLE_HRESULT(m_primaryBuffer->SetFormat(&waveFormat));
   }

   AudioClip::AudioClip(LPCWSTR filename) {
      unsigned int count;
      HRESULT result;
      IDirectSoundBuffer* tempBuffer;
      unsigned char* waveData;
      unsigned char *bufferPtr;
      unsigned long bufferSize;
      FileReader s(filename, std::ios::binary);
      char buf[4]{ 0 };
      while (s.IsOpen()) {
         buf[0] = buf[1];
         buf[1] = buf[2];
         buf[2] = buf[3];
         buf[3] = s.Read<char>();
         if (
            buf[0] == 'd' &&
            buf[1] == 'a' &&
            buf[2] == 't' &&
            buf[3] == 'a'
            ) {
            break;
         }
      }
      uint dataSize = s.Read<uint>();

      // Set the wave format of secondary buffer that this wave file will be loaded onto.
      WAVEFORMATEX waveFormat;
      waveFormat.wFormatTag = WAVE_FORMAT_PCM;
      waveFormat.nSamplesPerSec = 48000;
      waveFormat.wBitsPerSample = 16;
      waveFormat.nChannels = 1;
      waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
      waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
      waveFormat.cbSize = 0;

      // Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
      DSBUFFERDESC bufferDesc;
      bufferDesc.dwSize = sizeof(DSBUFFERDESC);
      bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
      bufferDesc.dwBufferBytes = dataSize;
      bufferDesc.dwReserved = 0;
      bufferDesc.lpwfxFormat = &waveFormat;
      bufferDesc.guid3DAlgorithm = GUID_NULL;
      //Now the way to create a secondary buffer is fairly strange.First step is that you create a temporary IDirectSoundBuffer with the sound buffer description you setup for the secondary buffer.If this succeeds then you can use that temporary buffer to create a IDirectSoundBuffer8 secondary buffer by calling QueryInterface with the IID_IDirectSoundBuffer8 parameter.If this succeeds then you can release the temporary buffer and the secondary buffer is ready for use.

         // Create a temporary sound buffer with the specific buffer settings.
      TE_HANDLE_HRESULT(m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL));

      // Test the buffer format against the direct sound 8 interface and create the secondary buffer.
      TE_HANDLE_HRESULT(tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_secondaryBuffer1));

      // Release the temporary buffer.
      tempBuffer->Release();
      tempBuffer = nullptr;
      //Now that the secondary buffer is ready we can load in the wave data from the audio file.First I load it into a memory buffer so I can check and modify the data if I need to.Once the data is in memory you then lock the secondary buffer, copy the data to it using a memcpy, and then unlock it.This secondary buffer is now ready for use.Note that locking the secondary buffer can actually take in two pointers and two positions to write to.This is because it is a circular buffer and if you start by writing to the middle of it you will need the size of the buffer from that point so that you don't write outside the bounds of it. This is useful for streaming audio and such. In this tutorial we create a buffer that is the same size as the audio file and write from the beginning to make things simple.

         // Move to the beginning of the wave data which starts at the end of the data chunk header.

      // Create a temporary buffer to hold the wave file data.
      waveData = new byte[dataSize];
      if (!waveData)
      {
         TE_ERROR("Not enough memory");
      }

      // Read in the wave file data into the newly created buffer.
      s.ReadBlock(waveData, dataSize);

      // Close the file once done reading.
      s.Close();

      // Lock the secondary buffer to write wave data into it.
      TE_HANDLE_HRESULT(m_secondaryBuffer1->Lock(0, dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0));

      // Copy the wave data into the buffer.
      memcpy(bufferPtr, waveData, dataSize);

      // Unlock the secondary buffer after the data has been written to it.
      TE_HANDLE_HRESULT(m_secondaryBuffer1->Unlock((void*)bufferPtr, bufferSize, NULL, 0));

      // Release the wave data since it was copied into the secondary buffer.
      delete[] waveData;
   }
   AudioClip::~AudioClip()
   {
      if (m_secondaryBuffer1)
      {
         m_secondaryBuffer1->Release();
         m_secondaryBuffer1 = nullptr;
      }
   }
   void AudioClip::PlayWaveFile() {
      // Set position at the beginning of the sound buffer.
      TE_HANDLE_HRESULT(m_secondaryBuffer1->SetCurrentPosition(0));

      // Set volume of the buffer to 100%.
      TE_HANDLE_HRESULT(m_secondaryBuffer1->SetVolume(DSBVOLUME_MAX));

      // Play the contents of the secondary sound buffer.
      TE_HANDLE_HRESULT(m_secondaryBuffer1->Play(0, 0, 0));
   }
   void AudioClip::Test() {
      
   }
}