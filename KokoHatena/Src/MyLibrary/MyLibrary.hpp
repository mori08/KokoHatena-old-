#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
#ifdef _DEBUG
	/// <summary>
	/// デバッグ用の文字列を出力
	/// </summary>
	/// <param name="message"> 出力する文字列 </param>
	inline void printDebug(const String& message)
	{
		Print << message;
	}
#else
	inline void printDebug(const String&)
	{

	}
#endif // _DEBUG

	/// <summary>
	/// アセット管理
	/// </summary>
	/// <param name="direName"> ディレクトリの名前 </param>
	void registerAsset(const String& dirName);

	/// <summary>
	/// 指定された頻度でランダムに 1 を出力
	/// </summary>
	/// <param name="frequency"> 頻度 (times/second) </param>
	/// <returns> 
	/// ランダムで 1 または 0 
	/// </returns>
	/// <remarks>
	/// 頻度がフレームレートを超えたとき, 毎フレーム 1 を出力
	/// </remarks>
	inline int32 randomFrequency(double frequency)
	{
		return (Random(1.0 / Scene::DeltaTime()) < frequency) ? 1 : 0;
	}

	/// <summary>
	/// 内分点を使った値の変更
	/// </summary>
	/// <param name="x"> 変更したい値     </param>
	/// <param name="a"> 目的値           </param>
	/// <param name="r"> 内分比(0,1) (/s) </param>
	/// <remarks>
	/// r には (0,1)の範囲の小数値
	/// 数値は0に近づけるほど速く移動
	/// </remarks>
	template<typename TYPE_X, typename TYPE_A>
	void internalDividingPoint(TYPE_X& x, const TYPE_A& a, double r)
	{
		r = Pow(r, Scene::DeltaTime());
		x = r * x + (1 - r) * a;
	}

	/// <summary>
	/// FPSの表示
	/// </summary>
	void showFPS();

	/// <summary>
	/// 中心座標を決めた長方形の取得
	/// </summary>
	/// <param name="center"> 中心座標 </param>
	/// <param name="size">   サイズ   </param>
	/// <returns> 長方形 </returns>
	inline constexpr Rect getRectFromCenter(const Point& center, const Size& size)
	{
		return std::move(Rect(center - size / 2, size));
	}

	/// <summary>
	/// 2頂点から長方形の取得
	/// </summary>
	/// <param name="pos1"> 頂点1 </param>
	/// <param name="pos2"> 頂点2 </param>
	/// <returns> 長方形 </returns>
	inline constexpr Rect getRectFromTwoPoint(const Point& pos1, const Point& pos2)
	{
		return std::move(Rect(Min(pos1.x, pos2.x), Min(pos1.y, pos2.y), Abs(pos1.x - pos2.x), Abs(pos1.y - pos2.y)));
	}

	/// <summary>
	/// 長方形内にある格子点のリストの取得
	/// </summary>
	/// <param name="rect"> 長方形 </param>
	/// <returns> 格子点 </returns>
	Array<Point> getGridPoint(const Rect& rect);

	/// <summary>
	/// 角度からその方向を向いた単位ベクトルを取得
	/// </summary>
	/// <param name="angle"> 角度(rad) </param>
	/// <returns> 単位ベクトル </returns>
	/// <remarks>
	/// 0(rad)をベクトル(1,0)に対応させ，
	/// 反時計回りを正の方向とする
	/// </remarks>
	inline constexpr Vec2 angleToVec(double angle)
	{
		return std::move(Vec2(Cos(angle), Sin(angle)));
	}

}