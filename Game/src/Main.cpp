#pragma comment(lib, "TEngine.lib")
#include <tengine.h>
using namespace TEngine;
using namespace std;
namespace TEngine::Application {
   struct Wheel {
      MeshRenderer *mr;
      bool braking;
      bool forcing;
      void Update() {

      }
   };
   Color backgroundColor;
   AudioClip *clip = nullptr;
   Mesh *mesh = nullptr;
   MeshRenderer *renderer = nullptr;
   MeshRenderer *wfr = nullptr;
   MeshRenderer *wfl = nullptr;
   MeshRenderer *wbr = nullptr;
   MeshRenderer *wbl = nullptr;
   Material *carMat = nullptr;
   Material *whlMat = nullptr;
   Shader *shader = nullptr;

   std::vector<std::pair<float3, float3>> lines;

   float3 velocity = 0;
   float aVelocity = 0;
   float friction = 0.025;
   float handBrake = 0;
   float3 calcWheelSideForce(MeshRenderer *wheel) {
      float3 result;
      /*Main Velocity*/ {
         result += velocity;
      }
      /* Angular Velocity */ {
         float3 diff = wheel->GetPosition() - renderer->GetPosition();
         auto cross = float3::Cross(diff, float3(0, 0, 1));
         result += cross * -aVelocity * PI;
      }
      return Lerp(result.ProjectedOn(wheel->GetRightDir()), result, handBrake * 0.5) * friction;
   }
   void addForceAtPos(float3 f, float3 wp, float3 &outVel, float &outAVel) {
      outVel += f;
      auto lp = wp - renderer->GetPosition();
      if (lp.LengthSqr() < 1.0f / (1 << 10)) {
         return;
      }
      //auto lf = *(float3*)&XMVector4Transform(XMVectorSet(f.x, f.y, f.z, 0), XMMatrixRotationRollPitchYawFromVector(renderer->_GetRotation()));
      auto cross = float3::Cross(lp, float3(0, 0, 1));
      outAVel -= f.ProjectedOn(cross).Length() * (float3::Dot(cross, f) > 0 ? 1 : -1) / 180;
      lines.emplace_back(wp, wp + f / FixedDelta);
   }
   // Called before initialization
   void Setup() {
      WindowName = L"TENGINE АПП ☺";
      UsingGraphicsAPI = GraphicsAPI::Direct3D11;
      //UpdateDelta = 0;
   }
   // Called after initialization
   void Start() {
      TE_PRINT("Aпплик старт");
      float3 verts[]{
         float3(-1,-2,1),
         float3(1,-2,1),
         float3(1, 2,1),
         float3(-1, 2,1),
         float3(0, 3, 1)
      };
      uint inds[]{
         2,1,0,3,2,0,2,3,4
      };
      TE_PRINT(float3(1, 0, 0).ProjectedOn(float3(5, 5, 0)));
      mesh = /*MeshCreator::Quad(1,1);//*/new Mesh(verts, 5, inds, 9);
      shader = Shader::CreateFromFile(L"data/shaders/testShader.hlsl");
      carMat = new Material(shader);
      whlMat = new Material(shader);
      float props[] = {
         1,0,0,0
      };
      carMat->SetProperties(props, 4);
      props[0] = 0;
      whlMat->SetProperties(props, 4);
      renderer = new MeshRenderer(mesh, carMat, 0, 0, 10);
      wfr = new MeshRenderer(mesh, whlMat, float3(10, 20, 0), 0, 0.2f);
      wfl = new MeshRenderer(mesh, whlMat, float3(-10, 20, 0), 0, 0.2f);
      wbr = new MeshRenderer(mesh, whlMat, float3(10, -20, 0), 0, 0.2f);
      wbl = new MeshRenderer(mesh, whlMat, float3(-10, -20, 0), 0, 0.2f);
      wfr->SetParent(renderer);
      wfl->SetParent(renderer);
      wbr->SetParent(renderer);
      wbl->SetParent(renderer);
      clip = new AudioClip(L"sound02.wav");
   }
   float xAxis = 0, yAxis = 0;
   // Call frequency depends on 'm_UpdateFrequency' field
   void Update() {
      if (Input::KeyDown(Key::F)) {
         shader->Release();
      }

      Renderer::instance->Clear(0.9);

      Renderer::instance->Draw(renderer);
      Renderer::instance->Draw(wfr);
      Renderer::instance->Draw(wfl);
      Renderer::instance->Draw(wbr);
      Renderer::instance->Draw(wbl);

      Renderer::instance->DrawLines((float3*)&lines[0], lines.size() * 2);
      
      std::vector<float3> points;
      points.reserve(Window::Width / 2);
      float (*calcVal)(float,float,float) = Math::SmoothStep5;
      points.emplace_back(-Window::Width / 2, calcVal(-Window::Width / 2, -Window::Height / 2, Window::Height / 2));
      for (int x = -Window::Width/2;x < Window::Width/2;x += 2) {
         points.emplace_back(x, calcVal(x, -Window::Height / 2, Window::Height / 2));
         points.emplace_back(x, calcVal(x, -Window::Height / 2, Window::Height / 2));
      }
      points.emplace_back(Window::Width / 2, calcVal(Window::Width / 2, -Window::Height / 2, Window::Height / 2));
      Renderer::instance->DrawLines(&points[0], points.size());

      if (Input::KeyDown(Key::P)) {
         TE_PRINT("Playing wav file");
         clip->PlayWaveFile();
      }
      auto yaxis = Input::KeyPair(Key::W, Key::S, Input::Axis::JoystickYPos);
      auto xaxis = Input::KeyPair(Key::A, Key::D, Input::Axis::JoystickXPos);
      if (Input::KeyHeld(Key::Space)) {
         handBrake = Lerp(handBrake, 1, Time.GetDelta() * 5);
      }
      else {
         handBrake = Lerp(handBrake, 0, Time.GetDelta() * 5);
      }
      xAxis = Math::Lerp(xAxis, xaxis, Time.GetDelta() * 5);
      yAxis = Math::Lerp(yAxis, yaxis, Time.GetDelta() * 5);
      wfr->SetRotation(0, 0, xAxis * QUARTPI);
      wfl->SetRotation(0, 0, xAxis * QUARTPI);

      //MessageBoxA(0, "Coupys: ", std::to_string(Math::copys).c_str(), MB_OK);
      //DebugBreak();
   }
   // Called at fixed rate
   void FixedUpdate() {
      lines.clear();
      velocity += (float3)renderer->GetUpDir() * yAxis * 500 * friction;
      velocity *= 0.999f;
      addForceAtPos(-calcWheelSideForce(wbl), wbl->GetPosition(), velocity, aVelocity);
      addForceAtPos(-calcWheelSideForce(wbr), wbr->GetPosition(), velocity, aVelocity);
      addForceAtPos(-calcWheelSideForce(wfl), wfl->GetPosition(), velocity, aVelocity);
      addForceAtPos(-calcWheelSideForce(wfr), wfr->GetPosition(), velocity, aVelocity);
      renderer->Rotate(0, 0, aVelocity * FixedDelta);
      //renderer->Rotate(0, 0, aVelocity = xAxis * m_Time.GetDelta() * 4);
      renderer->Translate(velocity * FixedDelta);
      if (renderer->GetLocalPosition().x > Window::Width / 2) renderer->SetPosition(renderer->GetLocalPosition() + float3(-Window::Width, 0, 0));
      if (renderer->GetLocalPosition().x < -Window::Width / 2) renderer->SetPosition(renderer->GetLocalPosition() + float3(Window::Width, 0, 0));
      if (renderer->GetLocalPosition().y > Window::Height / 2) renderer->SetPosition(renderer->GetLocalPosition() + float3(0, -Window::Height, 0));
      if (renderer->GetLocalPosition().y < -Window::Height / 2) renderer->SetPosition(renderer->GetLocalPosition() + float3(0, Window::Height, 0));
   }
   // Call frequency depends on monitor's refresh rate
   void Draw() {

   }
   // Called when the window has been resized
   void Resize() {

   }
   // Called when execution ends
   void Destroy() {
      delete clip;
      delete mesh;
      delete shader;
   }
};

TEngine::ApplicationSetupData SetupApp() {
   TEngine::ApplicationSetupData d;
   d.Setup = Application::Setup;
   d.Start = Application::Start;
   d.Destroy = Application::Destroy;
   d.Resize = Application::Resize;
   d.FixedUpdate = Application::FixedUpdate;
   d.Update = Application::Update;
   return d;
}