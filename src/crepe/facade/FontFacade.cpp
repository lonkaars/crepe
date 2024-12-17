#include <fontconfig/fontconfig.h>
#include <iostream>
#include <stdexcept>

#include "FontFacade.h"

using namespace crepe;
using namespace std;

FontFacade::FontFacade(){
	if (!FcInit()) {
		throw runtime_error("Failed to initialize Fontconfig.");
	}
}
FontFacade::~FontFacade(){
	FcFini();
}
Asset FontFacade::get_font_asset(const string& font_family) {
	
	// Create a pattern to search for the font family
	FcPattern * pattern = FcNameParse(reinterpret_cast<const FcChar8 *>(font_family.c_str()));
	if (!pattern) {
		throw runtime_error("Failed to create font pattern.");
	}

	// Default configuration
	FcConfig * config = FcConfigGetCurrent();
	if (config == NULL) {
		// FcPatternDestroy(pattern);
		throw runtime_error("Failed to get current Fontconfig configuration.");
	}

	// Match the font pattern
	FcResult result;
	FcPattern * matched_pattern = FcFontMatch(config, pattern, &result);
	FcPatternDestroy(pattern);

	if (!matched_pattern) {
		throw runtime_error("No matching font found.");
	}
	// Extract the file path
	FcChar8 * file_path = nullptr;
	if (FcPatternGetString(matched_pattern, FC_FILE, 0, &file_path) != FcResultMatch
		|| file_path == NULL) {
		// FcPatternDestroy(matched_pattern);
		throw runtime_error("Failed to get font file path.");
	}

	// Convert the file path to a string
	string font_file_path = reinterpret_cast<const char *>(file_path);
	FcPatternDestroy(matched_pattern);
	return Asset(font_file_path);
}
