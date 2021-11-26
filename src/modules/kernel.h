struct utsname uname_info;

void kernel()
{
	print("", "Kernel", uname_info.release);
}