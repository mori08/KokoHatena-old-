#include "MyLibrary.hpp"


namespace Kokoha
{

	void registerAsset(const String& dirName)
	{
		// 指定されたディレクトリのファイルパスを配列に
		Array<FilePath> contents = FileSystem::DirectoryContents(dirName, false);

		for (const auto& content : contents)
		{
			String fileName = FileSystem::FileName(content);

			// 指定されたパスがディレクトリであるとき
			if (FileSystem::IsDirectory(content))
			{
				registerAsset(dirName + fileName + U"/");
			}

			// 指定されたパスがファイルであるとき
			else if (FileSystem::IsFile(content))
			{
				// 拡張子がpngのとき
				if (FileSystem::Extension(content) == U"png")
				{
					TextureAsset::Register(FileSystem::BaseName(content), dirName + fileName);
				}

				// 拡張子がmp3のとき
				if (FileSystem::Extension(content) == U"mp3")
				{
					AudioAsset::Register(FileSystem::BaseName(content), dirName + fileName);
				}

			}
		}
	}


	void showFPS()
	{
#ifdef _DEBUG

		static std::list<double> fpsList;
		static Array<double> showNum(5, 60.0);

		double deltaTime = Scene::DeltaTime();
		if (deltaTime > 1.0 / 1e10 && deltaTime < 1e10)
		{
			fpsList.emplace_back(1 / deltaTime);
			if (fpsList.size() > 60) { fpsList.pop_front(); }
		}

		if (fpsList.size() < 60) { return; }

		std::vector<double> fpsVector;
		for (const auto& fps : fpsList) { fpsVector.emplace_back(fps); }
		std::sort(fpsVector.begin(), fpsVector.end());

		internalDividingPoint(showNum[0], fpsVector[0], 0.3);
		internalDividingPoint(showNum[1], (fpsVector[14] + fpsVector[15]) / 2, 0.3);
		internalDividingPoint(showNum[2], (fpsVector[29] + fpsVector[30]) / 2, 0.3);
		internalDividingPoint(showNum[3], (fpsVector[44] + fpsVector[45]) / 2, 0.3);
		internalDividingPoint(showNum[4], fpsVector[59], 0.3);

		const double rate = 800.0 / 60.0;
		const double offset = -400;

		Line(rate * showNum[0] + offset, 0, rate * showNum[4] + offset, 0).draw(8, Palette::Blue);
		Line(rate * showNum[1] + offset, 0, rate * showNum[3] + offset, 0).draw(10, Palette::Aqua);
		Circle(rate * showNum[2] + offset, 7, 2).draw(Palette::Aqua);
		FontAsset(U"20")(Profiler::FPS()).drawAt(rate * Profiler::FPS() + offset, 15, Palette::Aqua);

		FontAsset(U"10")((int32)showNum[0]).drawAt(Max(10.0, rate * showNum[0] + offset), 8, Palette::Blue);
		FontAsset(U"10")((int32)showNum[4]).drawAt(Min(790.0, rate * showNum[4] + offset), 8, Palette::Blue);

#endif // _DEBUG
	}


	Array<Point> getGridPoint(const Rect& rect)
	{
		Array<Point> rtn;

		for (int32 x : Range(rect.x, rect.x + rect.w))
		{
			for (int32 y : Range(rect.y, rect.y + rect.h))
			{
				rtn.emplace_back(x, y);
			}
		}

		return std::move(rtn);
	}

}