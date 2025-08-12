param name string
resource rg 'Microsoft.Resources/resourceGroups@2024-03-01' existing = { name: resourceGroup().name }

module env 'modules/aca-environment.bicep' = {
  name: 'acaEnv'
  params: { name: '${name}-env' }
}

module wp 'modules/aca-workloadprofile-gpu.bicep' = {
  name: 'wpGpu'
  params: { envName: env.outputs.name, gpuType: 'T4', minCount: 0, maxCount: 5 }
}

module funcGpu 'modules/function-on-aca.bicep' = {
  name: 'funcGpu'
  params: {
    name: 'gpu-preprocess'
    image: 'ACR_URL/gpu-preprocess:latest'
    workloadProfile: wp.outputs.name  // perfil con GPU
  }
}
