#pragma once

enum class FileType
{
	Folder = 0x01,		//文件夹
	Document = 0x02,	//文档
	Image = 0x04,		//图片
	Video = 0x08,		//视频
	Music = 0x10,		//音乐
	Other = 0x20,		//其它
};