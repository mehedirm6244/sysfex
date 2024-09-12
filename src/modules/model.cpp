#include <fstream>

#include <modules/model.hpp>

std::string model() {
  std::ifstream product_name("/sys/devices/virtual/dmi/id/product_name");
  if (!product_name.is_open()) {
    return "Unknown";
  }

  std::string model_name;
  getline(product_name, model_name);
  product_name.close();

  std::ifstream product_version("/sys/devices/virtual/dmi/id/product_version");
  if (!product_version.is_open()) {
    return "";
  }

  std::string model_version;
  getline(product_version, model_version);
  product_version.close();

  std::string output = model_name + " " + model_version;
  return output;
}
