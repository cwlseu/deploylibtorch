#include <torch/script.h> // One-stop header.

#include <iostream>
#include <memory>
#include "timer.hpp"

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		std::cerr << "usage: example-app <path-to-exported-script-module>\n";
		return -1;
	}
	torch::jit::script::Module module;
	try {
		// Deserialize the ScriptModule from a file using torch::jit::load().
		__TIC__(load)
		module = torch::jit::load(argv[1]);
		__TOC__(load)
	} catch (const c10::Error& e) {
		std::cerr << "error loading the model\n";
		return -1;
	}
	std::cout << "- model:" << argv[1] << std::endl;
	// Create a vector of inputs.
	std::vector<torch::jit::IValue> inputs;
	inputs.push_back(torch::ones({ 1, 3, 224, 224 }));

	// Execute the model and turn its output into a tensor.
	__TIC__(forward)
	at::Tensor output = module.forward(inputs).toTensor();
	__TOC__(forward)
	__TIC__(forward100times)
	for (int i = 0; i < 100; i++) {
		module.forward(inputs);
	}
	__TOC__(forward100times)
	// std::cout << output.slice(/*dim=*/1, /*start=*/0, /*end=*/5) << '\n';
	// std::cout << "test finished\n";
	return 0;
}
