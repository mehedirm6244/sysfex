string kernel()
{
	std::ifstream infile;
	infile.open("/proc/sys/kernel/osrelease");
    if (!(infile.is_open()))
		return exec(string("uname -r").c_str());

	string kernel;
	infile>>kernel;
	return kernel;
}