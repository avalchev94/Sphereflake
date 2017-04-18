#pragma once

class CApplication
{
public:
	CApplication(int argc, char** argv);
	~CApplication();

	int	OnExecute();

private:
	/// Input arguments ///
	int		fArgc;
	char**	fArgv;
};