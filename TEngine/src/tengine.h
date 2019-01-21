#pragma once
#include "core/common.h"
#include "core/core.h"
#include "core/console.h"
#include "core/input.h"
#include "core/graphics/mesh.h"
#include "core/graphics/MeshRenderer.h"
#include "core/graphics/shader.h"
extern TEngine::ApplicationSetupData SetupApp();
int main(int argc, char **argv, char **env) {
   TEngine::Run(argc, argv, env, SetupApp());
   return 0;
}
