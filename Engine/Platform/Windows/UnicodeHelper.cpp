#include "Platform/Windows/UnicodeHelper.h"
#include "Engine/System/UniquePtr.h"

using namespace Engine;
namespace Platform {
	UniquePtr<WCHAR[]> UnicodeHelper::UTF8ToUnicode(const String& string) {
		int32 len = MultiByteToWideChar(CP_UTF8, NULL, string.GetRawArray(), -1, NULL, 0);
		if (len <= 0) {
			throw Exception("UnicodeHelper::UTF8ToUnicode: MultiByteToWideChar calculate required wide char length failed!");
		}
		UniquePtr<WCHAR[]> wchar = UniquePtr<WCHAR[]>(new WCHAR[len]());

		int32 converted = MultiByteToWideChar(CP_UTF8, NULL, string.GetRawArray(), string.GetLength() + 1, wchar.get(), len);
		if (converted <= 0) {
			throw Exception("UnicodeHelper::UTF8ToUnicode: MultiByteToWideChar converting failed!");
		}
		return wchar;
	}

	String UnicodeHelper::UnicodeToUTF8(WCHAR* unicode) {
		int32 len = WideCharToMultiByte(CP_UTF8, NULL, unicode, -1, NULL, 0, NULL, NULL);
		if (len <= 0) {
			throw Exception("UnicodeHelper::UnicodeToUTF8: WideCharToMultiByte calculate required char length failed!");
		}
		UniquePtr<char[]> chars = UniquePtr<char[]>(new char[len]());

		int32 converted = WideCharToMultiByte(CP_UTF8, NULL, unicode, -1, chars.get(), len, NULL, NULL);
		if (converted <= 0) {
			throw Exception("UnicodeHelper::UTF8ToUnicode: MultiByteToWideChar converting failed!");
		}
		return String(chars.get());
	}
}