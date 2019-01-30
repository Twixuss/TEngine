#define TENGINE_USE_SOURCE 1
#define TENGINE_USE_INTRINSICS 1
#include <TEngine.h>
using namespace TEngine;
using namespace std;
struct Game : public TEngine::Application
{
   struct Wheel
   {
      MeshRenderer *mr;
      bool braking;
      bool forcing;
      void Update()
      {
         
      }
   };
   Color backgroundColor;
   AudioClip *clip = nullptr;
   Mesh *mesh = nullptr;
   MeshRenderer *car = nullptr;
   MeshRenderer *wfr = nullptr;
   MeshRenderer *wfl = nullptr;
   MeshRenderer *wbr = nullptr;
   MeshRenderer *wbl = nullptr;
   Material *carMat = nullptr;
   Material *whlMat = nullptr;

   //std::vector<std::pair<float3, float3>> lines;

   float3 velocity = 0;
   float aVelocity = 0;
   float friction = 0.25;
   float handBrake = 0;
   float3 calcWheelSideForce(MeshRenderer *wheel)
   {

      float3 result;
      /*Main Velocity*/
      {
         result += velocity;
      }
      /* Angular Velocity */
      {
         float3 diff = wheel->GetPosition() - car->GetPosition();
         auto cross = float3::Cross(diff, float3(0, 0, 1));
         result += cross * -aVelocity * PI;
      }
      return Lerp(result.ProjectedOn(wheel->GetRightDir()), result, handBrake * 0.5) * friction;
   }
   void addForceAtPos(float3 f, float3 wp, float3 &outVel, float &outAVel)
   {
      outVel += f;
      auto lp = wp - car->GetPosition();
      if (lp.LengthSqr() < 1.0f / (1 << 10))
      {
         return;
      }
      //auto lf = *(float3*)&XMVector4Transform(XMVectorSet(f.x, f.y, f.z, 0), XMMatrixRotationRollPitchYawFromVector(renderer->_GetRotation()));
      auto cross = float3::Cross(lp, float3(0, 0, 1));
      outAVel -= f.ProjectedOn(cross).Length() * (float3::Dot(cross, f) > 0 ? 1 : -1) / 180 * PI;
      //lines.emplace_back(wp, wp + f / m_FixedDelta);
   }
   Game() : TEngine::Application(L"TEngine", 800, 800)
   {
      //m_WindowName = L"TENGINE АПП ☺";
      m_GraphicsAPI = GraphicsAPI::Direct3D11;
      //m_UpdateDelta = 0;
      //m_UpdateDelta = 1.0f / 100.0f;
   }
   void Start() override
   {
      TE_PRINT("Aпплик старт");
      float3 verts[]{
         float3(-1,-2,0),
         float3(1,-2 ,0),
         float3(1, 2 ,0),
         float3(-1, 2,0),
         float3(0, 3, 0)
      };
      uint inds[]{
         2,1,0,3,2,0,2,3,4
      };
      TE_PRINT(float3(1, 0, 0).ProjectedOn(float3(5, 5, 0)));
      mesh = m_Renderer->CreateMesh(verts, 5, inds, 9);
      carMat = m_Renderer->GetMaterial(L"data\\materials\\car.mat");
      whlMat = m_Renderer->GetMaterial(L"data\\materials\\wheel.mat");
      car = m_Renderer->CreateMeshRenderer(mesh, carMat, float3(0, 0, 0.1), 0, 10);
      wfr = m_Renderer->CreateMeshRenderer(mesh, whlMat, float3(10, 20, -0.01), 0, 0.2f);
      wfl = m_Renderer->CreateMeshRenderer(mesh, whlMat, float3(-10, 20, -0.01), 0, 0.2f);
      wbr = m_Renderer->CreateMeshRenderer(mesh, whlMat, float3(10, -20, -0.01), 0, 0.2f);
      wbl = m_Renderer->CreateMeshRenderer(mesh, whlMat, float3(-10, -20, -0.01), 0, 0.2f);
      wfr->SetParent(car);
      wfl->SetParent(car);
      wbr->SetParent(car);
      wbl->SetParent(car);
      clip = new AudioClip(L"sound02.wav");
   }
   float xAxis = 0, yAxis = 0;
   KeyAxis yaxis = KeyAxis(m_Keyboard, m_Joystick, Key::W, Key::S, Joystick::Axis::YPos);
   KeyAxis xaxis = KeyAxis(m_Keyboard, m_Joystick, Key::A, Key::D, Joystick::Axis::XPos);
   void Update()override
   {
      if (m_Keyboard.KeyDown(Key::P))
      {
         TE_PRINT("Playing wav file");
         clip->PlayWaveFile();
      }
      if (m_Keyboard.KeyHeld(Key::Space))
      {
         handBrake = Lerp(handBrake, 1, m_Time.GetDelta() * 5);
      }
      else
      {
         handBrake = Lerp(handBrake, 0, m_Time.GetDelta() * 5);
      }
      xAxis = Math::Lerp(xAxis, xaxis.Get(), m_Time.GetDelta() * 5);
      yAxis = Math::Lerp(yAxis, yaxis.Get(), m_Time.GetDelta() * 5);
      wfr->SetRotation(0, 0, xAxis * QUARTPI);
      wfl->SetRotation(0, 0, xAxis * QUARTPI);

      //MessageBoxA(0, "Coupys: ", std::to_string(Math::copys).c_str(), MB_OK);
      //DebugBreak();
   }
   void FixedUpdate()override
   {
      //lines.clear();
      velocity += (float3)car->GetUpDir() * yAxis * 500 * friction;
      velocity *= 0.999f;
      addForceAtPos(-calcWheelSideForce(wbl), wbl->GetPosition(), velocity, aVelocity);
      addForceAtPos(-calcWheelSideForce(wbr), wbr->GetPosition(), velocity, aVelocity);
      addForceAtPos(-calcWheelSideForce(wfl), wfl->GetPosition(), velocity, aVelocity);
      addForceAtPos(-calcWheelSideForce(wfr), wfr->GetPosition(), velocity, aVelocity);
      car->Rotate(0, 0, aVelocity * m_FixedDelta);
      //renderer->Rotate(0, 0, aVelocity = xAxis * m_Time.GetDelta() * 4);
      car->Translate(velocity * m_FixedDelta);
      if (car->GetLocalPosition().x > m_Window.GetClientWidth() / 2) car->SetPosition(car->GetLocalPosition() + float3(-m_Window.GetClientWidth(), 0, 0));
      if (car->GetLocalPosition().x < -m_Window.GetClientWidth() / 2) car->SetPosition(car->GetLocalPosition() + float3(m_Window.GetClientWidth(), 0, 0));
      if (car->GetLocalPosition().y > m_Window.GetClientHeight() / 2) car->SetPosition(car->GetLocalPosition() + float3(0, -m_Window.GetClientHeight(), 0));
      if (car->GetLocalPosition().y < -m_Window.GetClientHeight() / 2) car->SetPosition(car->GetLocalPosition() + float3(0, m_Window.GetClientHeight(), 0));
   }
   void Draw()override
   {
      m_Renderer->Clear(0.9);

      //car->GetMaterial()->SetFloat(0, sin(m_Time.GetTotalTime()));
      m_Renderer->Draw(car);
      m_Renderer->Draw(wfr);
      m_Renderer->Draw(wfl);
      m_Renderer->Draw(wbr);
      m_Renderer->Draw(wbl);

      //if(lines.size() > 1)
      //m_Renderer->DrawLines((float3*)&lines[0], lines.size() * 2);

      //std::vector<float3> points;
      //points.reserve(m_Window.GetClientWidth() / 2);
      //float(*calcVal)(float, float, float) = Math::SmoothStep5;
      //points.emplace_back(-m_Window.GetClientWidth() / 2, calcVal(-m_Window.GetClientWidth() / 2, -m_Window.GetClientHeight() / 2, m_Window.GetClientHeight() / 2));
      //for (int x = -m_Window.GetClientWidth() / 2;x < m_Window.GetClientWidth() / 2;x += 2)
      //{
      //   points.emplace_back(x, calcVal(x, -m_Window.GetClientHeight() / 2, m_Window.GetClientHeight() / 2));
      //   points.emplace_back(x, calcVal(x, -m_Window.GetClientHeight() / 2, m_Window.GetClientHeight() / 2));
      //}
      //points.emplace_back(m_Window.GetClientWidth() / 2, calcVal(m_Window.GetClientWidth() / 2, -m_Window.GetClientHeight() / 2, m_Window.GetClientHeight() / 2));
      //m_Renderer->DrawLines(&points[0], points.size());
   }
   void Resize()override
   {

   }
   ~Game()
   {
      delete clip;
      delete mesh;
      delete car;
      delete wfr;
      delete wfl;
      delete wbr;
      delete wbl;
   }
};

TEngine::Application* SetupApp()
{
   return new ::Game();
}