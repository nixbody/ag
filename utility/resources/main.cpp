#include <algorithm>
#include <cctype>
#include <cstddef>
#include <experimental/filesystem>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

namespace fs = std::experimental::filesystem;
struct resource final { const std::string encoded_data; const std::size_t size; };

/* Get the given resource name. */
auto resource_name(const fs::directory_entry &entry)
{
	static std::regex r{"[^0-9A-Za-z]"};

	std::string name{std::regex_replace(entry.path().filename().string(), r, "_")};
	std::transform(name.cbegin(), name.cend(), name.begin(), ::tolower);

	return name;
}

/* Encode the given resource as an array of characters. */
resource encode_resource(const fs::directory_entry &entry)
{
	std::ifstream in{entry, std::ios::binary};
	std::stringstream buff;
	std::stringstream out;
	std::size_t size{0};

	buff << in.rdbuf();
	out << '{';
	for (const auto c : buff.str()) {
		if (size) out << ", ";
		out << "std::byte{" << unsigned{static_cast<unsigned char>(c)} << "}";
		++size;
	}
	out << '}';

	return {out.str(), size};
}

/* Convert resource files to C++ files so they can be embedded into an executable file. */
int main()
{
	std::ofstream hpp{"../../ag/resources.h"};

	hpp << "#pragma once\n\n#include <array>\n#include <cstddef>\n\nnamespace ag::resources\n{\n";
	for (const auto &entry : fs::directory_iterator{"../../resources/"}) {
		const auto name = resource_name(entry);
		const auto resource = encode_resource(entry);
		std::ofstream cpp{(std::string("../../ag/resources/") += name) += ".cpp"};

		hpp << "\tstd::array<std::byte, " << resource.size << "> &" << name << "();\n";
		cpp << "#include <array>\n#include <cstddef>\n\nnamespace ag::resources\n{"
			<< "\n\tauto &" << name << "()\n\t{\n\t\tstatic std::array<std::byte, " << resource.size << "> data"
			<< resource.encoded_data << ";\n\t\treturn data;\n\t}\n}\n";
	}
	hpp << "}\n";

	return 0;
}
