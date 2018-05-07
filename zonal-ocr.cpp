#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#define DENSITY 200

int main(int argc, char *argv[])
{
	char* outText;
	int densidad, left, top, width, height;
	int escalado_coord = 1;
	
	if (argc != 8)
	{
		fprintf(stderr, "Número de parámetros incorrectos.\n");
		fprintf(stderr, "Forma correcta: %s <imagen-a-analizar> <densidad> <whitelist> <left> <top> <width> <height>\n",argv[0]);
		exit(1);
	}

	densidad = atoi(argv[2]);
	left = atoi(argv[4]);
	top = atoi(argv[5]);
	width = atoi(argv[6]);
	height = atoi(argv[7]);


	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with language, without specifying tessdata path
	if (api->Init(NULL, "spa+eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	// Open input image with leptonica library
	Pix *image = pixRead(argv[1]);
	api->SetImage(image);
	
	escalado_coord = densidad/DENSITY;

	//Disable dictionary and frequent words
	api->SetVariable("load_system_dawg","0");
	api->SetVariable("load_freq_dawg","0");
	//Limit the character set the Tesseract should try to recognize from
	api->SetVariable("tessedit_char_whitelist",argv[3]);
	

	// Limit the OCR to rectangle
	api->SetRectangle(left/escalado_coord, top/escalado_coord, width/escalado_coord, height/escalado_coord);

	// Get OCR result
	outText = api->GetUTF8Text();
	printf("OCR output:\n%s", outText);

	// Destroy used object and release memory
	api->End();
	delete [] outText;
	pixDestroy(&image);

	return 0;
}
