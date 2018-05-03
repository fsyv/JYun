#include "stdafx.h"
#include "OtherFile.h"


OtherFile::OtherFile() :
	File(FileType::Other)
{
	
}


OtherFile::~OtherFile()
{
}

bool OtherFile::preview()
{
	return false;
}

