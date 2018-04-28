#include <algorithm>
#include <cctype>
#include <experimental/filesystem>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

namespace fs = std::experimental::filesystem;

/* Get the given resource name. */
std::string resource_name(const fs::directory_entry &entry)
{
	static std::regex r{"[^0-9A-Za-z]"};

	std::string name{std::regex_replace(entry.path().filename().string(), r, "_")};
	std::transform(name.cbegin(), name.cend(), name.begin(), ::tolower);

	return name;
}

/* Encode the given resource as an array of characters. */
std::string encode_resource(const fs::directory_entry &entry)
{
	std::ifstream in{entry, std::ios::binary};
	std::stringstream buff;
	std::stringstream out;

	buff << in.rdbuf();
	for (const auto c : buff.str()) {
		out << ',' << static_cast<int>(c);
	}

	std::string str{out.str() += '}'};
	str[0] = '{';

	return str;
}

/* Convert resource files to C++ files so they can be embedded into an executable file. */
int main()
{
	std::ofstream hpp{"../ag/resources.h"};

	hpp << "#pragma once\n\n#include <string>\n\nnamespace ag::resources\n{\n";
	for (const auto &entry : fs::directory_iterator{"../resources/"}) {
		const auto name = resource_name(entry);
		std::ofstream cpp{(std::string("../ag/resources/") += name) += ".cpp"};

		hpp << "\tconst std::string &" << name << "();\n";
		cpp << "#include <string>\n\nnamespace ag::resources\n{"
			<< "\n\tconst std::string &" << name
			<< "()\n\t{\n\t\tstatic const std::string data = " << encode_resource(entry)
			<< ";\n\t\treturn data;\n\t}\n}\n";
	}
	hpp << "}\n";

	return 0;
}
