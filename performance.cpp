#include <torch/script.h> // One-stop header.

#include <iostream>
#include <memory>
#include "timer.hpp"
#include <cstring>
#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

// struct dirent {
// 	long d_ino; /* inode number 索引节点号 */
// 	off_t d_off; /* offset to this dirent 在目录文件中的偏移 */
// 	unsigned short d_reclen;  // length of this d_name 文件名长 
// 	unsigned char d_type; /* the type of d_name 文件类型 */
// 	char d_name [NAME_MAX+1]; /* file name (null-terminated) 文件名，最长255字符 */
// }

inline bool is_trace_pth(struct dirent *dirp) {
	int len = strlen(dirp->d_name);
	char suffix[] = "-trace.pt";
	int suffix_len = strlen(suffix);
	// fprintf(stderr, "%d %d %d %c\n", strlen(dirp->d_name), len, suffix_len, dirp->d_name[len - suffix_len]);
	return memcmp(&(dirp->d_name[len - suffix_len]), suffix, suffix_len) == 0;
}

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage:%s <path-to-model-dir>\n", argv[0]);
		return -1;
	}
	torch::jit::script::Module module;

	DIR *dp;
    struct dirent *dirp;
    std::string dirname(argv[1]);
    if((dp = opendir(dirname.c_str())) == NULL) {
    	fprintf(stderr, "Can't open %s\n", dirname.c_str());
		return -1;
	}
	while((dirp = readdir(dp)) != NULL) {
		if(!is_trace_pth(dirp)) continue;
		std::string model_path = dirname + "/" + dirp->d_name;
		fprintf(stderr, "-model:%s\n", model_path.c_str());
		try {
			// Deserialize the ScriptModule from a file using torch::jit::load().
			__TIC__(  load)
			module = torch::jit::load(model_path);
			__TOC__(  load)
		} catch (const c10::Error& e) {
			std::cerr << "error loading the model\n";
			return -1;
		}
		// Create a vector of inputs.
		std::vector<torch::jit::IValue> inputs;
		inputs.push_back(torch::ones({ 1, 3, 224, 224 }));

		// Execute the model and turn its output into a tensor.
		__TIC__(  forward)
		at::Tensor output = module.forward(inputs).toTensor();
		__TOC__(  forward)
	}
	closedir(dp);
	// std::cout << output.slice(/*dim=*/1, /*start=*/0, /*end=*/5) << '\n';
	// std::cout << "test finished\n";
	return 0;
}
