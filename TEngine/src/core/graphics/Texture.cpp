#include "Texture.h"
#include "renderer.h"
namespace TEngine {
   Texture::Texture(CWString filename) {
      //m_ID = Renderer::instance->GetNewTextureID();
      //Renderer::instance->CreateTextureFromFile(m_ID);
   }

   Texture::~Texture() {
      Release();
   }

   void Texture::SetToSlot(uint slot) {
      //Renderer::instance->SetTextureToSlot(slot);
   }

   void Texture::Release() {
      //Renderer::instance->ReleaseTexture(this);
   }
}
