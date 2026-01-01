#include "Framework.h"
#include "VertexShader.h"


VertexShader::VertexShader(wstring file)
{
    /* Vertex Shader */

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    file = L"_Shader/" + file + L".hlsl";

    assert(PathFileExistsW(file.c_str()));
    
    D3DCompileFromFile
    (
        file.c_str(),
        nullptr,
        nullptr,
        "main",
        "vs_5_0",
        flags,
        0,
        &blob,
        nullptr
    );

    DEVICE->CreateVertexShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &vertexShader
    );

    CreateInputLayout();

}

VertexShader::~VertexShader()
{
    blob->Release(); // 단순히 shader 정보를 불러와서 vertexShader를 만드는 데 필요함
    vertexShader->Release();
    inputLayout->Release();
    reflection->Release();
}

void VertexShader::SetShader()
{
    DC->IASetInputLayout(inputLayout);

    DC->VSSetShader(vertexShader, nullptr, 0);
}

void VertexShader::CreateInputLayout()
{
    //D3D11_INPUT_ELEMENT_DESC layoutDesc[2] = {};
    //layoutDesc[0].SemanticName = "POSITION";                        // Semantic은 이 변수의 의미 또는 용도를 쓰면 됨
    //layoutDesc[0].SemanticIndex = 0;
    //layoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    //layoutDesc[0].InputSlot = 0;
    //layoutDesc[0].AlignedByteOffset = 0;
    //layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    //layoutDesc[0].InstanceDataStepRate = 0;

    ////layoutDesc[1].SemanticName = "COLOR";
    ////layoutDesc[1].SemanticIndex = 0;                                // color의 정보가 여러개 있을 수 있음 (color0 color1 color2)
    ////layoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    ////layoutDesc[1].InputSlot = 0;
    ////layoutDesc[1].AlignedByteOffset = 12;                           // 앞에 (Position)12바이트가 채워져 있어서 offset으로 건너 뛰어야 함
    ////layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    ////layoutDesc[1].InstanceDataStepRate = 0;

    //layoutDesc[1].SemanticName = "UV";
    //layoutDesc[1].SemanticIndex = 0;                                // color의 정보가 여러개 있을 수 있음 (color0 color1 color2)
    //layoutDesc[1].Format = DXGI_FORMAT_R32G32_FLOAT;
    //layoutDesc[1].InputSlot = 0;
    //layoutDesc[1].AlignedByteOffset = 12;                           // 앞에 (Position)12바이트가 채워져 있어서 offset으로 건너 뛰어야 함
    //layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    //layoutDesc[1].InstanceDataStepRate = 0;

    //UINT layoutSize = ARRAYSIZE(layoutDesc);                        // 배열의 길이를 구하는 메크로 함수

    //DEVICE->CreateInputLayout
    //(
    //    layoutDesc,
    //    layoutSize,
    //    blob->GetBufferPointer(),
    //    blob->GetBufferSize(),
    //    &inputLayout
    //);

    D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection);

    D3D11_SHADER_DESC shaderDesc;
    reflection->GetDesc(&shaderDesc);

    vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;

    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = paramDesc.SemanticName;
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        if (paramDesc.Mask < 2)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask < 4)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask < 8)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask < 16)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        string semantic = paramDesc.SemanticName;

        if (semantic == "POSITION")
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        inputLayouts.push_back(elementDesc);
    }

    DEVICE->CreateInputLayout
    (
        inputLayouts.data(),
        inputLayouts.size(),
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        &inputLayout
    );
}
