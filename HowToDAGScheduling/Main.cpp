# include <Siv3D.hpp> // OpenSiv3D v0.6.6
# include "DAG.h"

void Main()
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(Palette::Lightgreen);

	Array<Node> nodes =
	{
		Node(0, 10, Point(0, 1)),
		Node(1, 8, Point(1, 0)),
		Node(2, 6, Point(1, 1)),
		Node(3, 7, Point(1, 2)),
		Node(4, 9, Point(2, 1))
	};

	Array<Array<int>> edges =
	{
		Array<int>{0, 1}, Array<int>{0, 2}, Array<int>{0, 3},
		Array<int>{1, 4}, Array<int>{2, 4}, Array<int>{3, 4}
	};

	DAG dag = DAG(nodes, edges, Point(64, 64));

	while (System::Update())
	{
		dag.draw();
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要です。
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/tutorial/
//
// Tutorial
// https://siv3d.github.io/tutorial/tutorial/
//
// Siv3D コミュニティへの参加（Discord などで気軽に質問や交流, 最新情報の入手ができます）
// https://siv3d.github.io/ja-jp/community/community/
//
// Siv3D User Community
// https://siv3d.github.io/community/community/
//
// 新機能の提案やバグの報告 | Feedback
// https://siv3d.github.io/ja-jp/develop/report/
//
// Sponsoring Siv3D
// https://github.com/sponsors/Reputeless
//
