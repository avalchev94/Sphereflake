#include "Application.h"

int main(int argc, char** argv)
{	
	CApplication app(argc, argv);

	return app.OnExecute();
}