#pragma once

namespace Utility
{
	string ToString(wstring value);
	wstring ToWstring(string value);

	vector<string> SplitString(string origin, string tok);
	void Replace(string* str, string comp, string rep);

	wstring GetExtension(wstring path);
	string GetDirectoryName(string path);
	string GetFileName(string path);
	string GetFileNameWithoutExtension(string path);

	void ToUpper(string& value);

	bool ExistFile(string path);
	bool ExistDirectory(string path);
	void CreateFolders(string path);

};