#include "util/melon.h"

int DrObfuscateMain(DgArgs *args) {
	const char *file_in = DgArgGetValue2(args, "i", "file://input.dat");
	const char *file_out = DgArgGetValue2(args, "o", "file://output.dat");
	const char *algorithm = DgArgGetValue2(args, "a", "none");
	const char *password = DgArgGetValue2(args, "p", "password");
	bool decrypt = DgArgGetFlag(args, "d");
	bool time_test = DgArgGetFlag(args, "t");
	
	DgObfuscateAlgorithm algorithm_id;
	
	if (DgStringEqual(algorithm, "rot13")) {
		algorithm_id = DG_OBFUSCATE_ROT13;
	}
	else if (DgStringEqual(algorithm, "cesar")) {
		algorithm_id = DG_OBFUSCATE_CESAR;
	}
	else if (DgStringEqual(algorithm, "poly")) {
		algorithm_id = DG_OBFUSCATE_POLYALPHABETIC;
	}
	else if (DgStringEqual(algorithm, "mediocre")) {
		algorithm_id = DG_OBFUSCATE_MEDIOCRE;
	}
	else if (DgStringEqual(algorithm, "sea1")) {
		algorithm_id = DG_OBFUSCATE_SEA1;
	}
	else if (DgStringEqual(algorithm, "sea2")) {
		algorithm_id = DG_OBFUSCATE_SEA2;
	}
	
	DgLog(DG_LOG_INFO, "Input file: %s", file_in);
	DgLog(DG_LOG_INFO, "Output file: %s", file_out);
	
	// Load the file
	DgError status;
	size_t length;
	void *data;
	
	status = DgFileLoad(NULL, file_in, &length, &data);
	
	if (status) {
		DgLog(DG_LOG_FATAL, "Failed to load input file!");
		return 1;
	}
	
	DgLog(DG_LOG_INFO, "Loaded file...");
	
	double time = DgTime();
	
	if (!decrypt) {
		DgObfuscateData(algorithm_id, password, length, data);
	}
	else {
		DgDeobfuscateData(algorithm_id, password, length, data);
	}
	
	time = DgTime() - time;
	
	if (time_test) {
		DgLog(DG_LOG_INFO, "Took %gms to encrypt 0x%x byte message", time * 1000.0f, length);
	}
	
	DgLog(DG_LOG_INFO, "Data transformed...");
	
	status = DgFileSave(NULL, file_out, length, data);
	
	if (status) {
		DgLog(DG_LOG_FATAL, "Failed to save output file! (status = 0x%x)", status);
		return 1;
	}
	
	DgLog(DG_LOG_INFO, "Saved file...");
	
	DgArgFree(&args);
	
	return 0;
}
