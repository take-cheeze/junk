#include <torch/extension.h>
PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
       m.def("debug", [](double sc){ return sc; });
}
