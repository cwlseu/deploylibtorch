# deploylibtorch
deploy some algorithm using libtorch

## For what?
Landing in different businesses is an essential capability in current CV and NLP research areas. The implementation of the algorithm has to consider performance and efficiency, and the use of C++ library in the open source training framework for project implementation is currently the first choice of many companies when starting new business. As the algorithm production tool of many algorithm researchers, libtorch is favored by pytorcher for its features of easy migration and high efficiency.


## build

cmake -G "Visual Studio 14 Win64" -DCMAKE_PREFIX_PATH=../deps/windows-x86_64/libtorch/share/cmake ..

## models

test_model: mobilenetv2-trace.pt https://pan.baidu.com/s/1neHRHypYq9vbGDlY1WwfJw  code:sym8
|model| download| |
|:---:|:---:|:-----:|
|mobilenet| | |

## FAQ
1. windows-x86-vs2015 "formal parameter with requested alignment of 16 won't be aligned"

Sol 1： update vs2015 to vs2019 https://github.com/pytorch/pytorch/issues/34124
Sol 2： only build win64`cmake -G "Visual Studio 14 Win64" ..`

2. gcc 版本要 >= 5.0， 但是当version >=5.1 会面临GCC ABI的问题
https://github.com/pytorch/pytorch/issues/14620