#!/usr/bin/python3
#-*-encoding=utf-8-*-
import torch
import torchvision.models as models

__doc__ = """
torchvision包 包含了目前流行的数据集，模型结构和常用的图片转换工具。
就是说我们重设计模型的话，可以从这里开始，预训练的模型，数据集合，预处理方法
"""

def pretrained_model(name):
    if name == "resnet18":
        return models.resnet18(pretrained=True)
    elif name == "alexnet":
        return models.alexnet(pretrained=True)
    elif name == "squeezenet":
        return models.squeezenet1_0(pretrained=True)
    elif name == "vgg16":
        return models.vgg16(pretrained=True)
    elif name == "densenet":
        return models.densenet161(pretrained=True)
    elif name == "inception":
        return models.inception_v3(pretrained=True)
    elif name == "googlenet":
        return models.googlenet(pretrained=True)
    elif name == "shufflenet": 
        return models.shufflenet_v2_x1_0(pretrained=True)
    elif name == "mobilenet":
        return models.mobilenet_v2(pretrained=True)
    elif name == "resnext50_32x4d":
        return models.resnext50_32x4d(pretrained=True)
    elif name == "wide_resnet50_2":
        return models.wide_resnet50_2(pretrained=True)
    elif name == "mnasnet":
        return models.mnasnet1_0(pretrained=True)
    else:
        print("model {} don't know".format(name))


def main():
    models_name = ["resnet18","alexnet","squeezenet","vgg16","densenet","inception","googlenet","shufflenet","mobilenet","resnext50_32x4d","wide_resnet50_2","mnasnet"]
    example = torch.rand(1, 3, 224, 224)
    for model_name in models_name:
        print("- load pretrained model: {}".format(model_name))
        model = pretrained_model(model_name)
        model = model.eval()
        model.forward(example)
        traced_script_module = torch.jit.trace(model, example)
        output = traced_script_module(torch.ones(1, 3, 224, 224))
        print("  resave script model: {}".format(model_name))
        traced_script_module.save('{}-trace.pt'.format(model_name))


if __name__ == '__main__':
    main()