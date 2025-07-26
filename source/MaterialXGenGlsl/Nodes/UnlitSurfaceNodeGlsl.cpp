//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXGenGlsl/Nodes/UnlitSurfaceNodeGlsl.h>

#include <MaterialXGenShader/Shader.h>
#include <MaterialXGenShader/GenContext.h>

MATERIALX_NAMESPACE_BEGIN

ShaderNodeImplPtr UnlitSurfaceNodeGlsl::create()
{
    return std::make_shared<UnlitSurfaceNodeGlsl>();
}

void UnlitSurfaceNodeGlsl::emitFunctionCall(const ShaderNode& node, GenContext& context, ShaderStage& stage) const
{
    const GlslShaderGenerator& shadergen = static_cast<const GlslShaderGenerator&>(context.getShaderGenerator());

    DEFINE_SHADER_STAGE(stage, Stage::PIXEL)
    {
        // Declare the output variable
        const ShaderOutput* output = node.getOutput();
        shadergen.emitLineBegin(stage);
        shadergen.emitOutput(output, true, true, context, stage);
        shadergen.emitLineEnd(stage);

        const string outAlbedo = output->getVariable() + ".albedo";
        const string outEmission = output->getVariable() + ".emission";
        const string outRoughness = output->getVariable() + ".roughness";
        // const string outTransparency = output->getVariable() + ".transparency";

        const ShaderInput* albedo = node.getInput("albedo");
        const ShaderInput* albedoColor = node.getInput("albedo_color");
        shadergen.emitLine(outAlbedo + " = " + shadergen.getUpstreamResult(albedo, context) + " * " + shadergen.getUpstreamResult(albedoColor, context), stage);

        const ShaderInput* emission = node.getInput("emission");
        const ShaderInput* emissionColor = node.getInput("emission_color");
        shadergen.emitLine(outEmission + " = " + shadergen.getUpstreamResult(emission, context) + " * " + shadergen.getUpstreamResult(emissionColor, context), stage);

        const ShaderInput* roughness = node.getInput("roughness");
        shadergen.emitLine(outRoughness + " = " + shadergen.getUpstreamResult(roughness, context), stage);

        // const ShaderInput* transmission = node.getInput("transmission");
        // const ShaderInput* transmissionColor = node.getInput("transmission_color");
        // shadergen.emitLine(outTransparency + " = " + shadergen.getUpstreamResult(transmission, context) + " * " + shadergen.getUpstreamResult(transmissionColor, context), stage);

        // const ShaderInput* opacity = node.getInput("opacity");
        // const string surfaceOpacity = shadergen.getUpstreamResult(opacity, context);
        // shadergen.emitLine(outColor + " *= " + surfaceOpacity, stage);
        // shadergen.emitLine(outTransparency + " = mix(vec3(1.0), " + outTransparency + ", " + surfaceOpacity + ")", stage);
    }
}

MATERIALX_NAMESPACE_END
