#include "stdafx.h"
#include "OtherFile.h"


OtherFile::OtherFile(Folder *parent) :
	File(FileType::Other, parent)
{
	
}


OtherFile::~OtherFile()
{
}

bool OtherFile::preview()
{
	return false;
}

