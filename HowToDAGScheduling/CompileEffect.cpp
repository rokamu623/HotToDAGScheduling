#include "stdafx.h"
#include "CompileEffect.h"

CompileEffect::CompileEffect(String text, Color color)
{
	_feed_in = true;
	_color = color;
	_color.setA(0);
	_font = Font(128);
	_wait = 60;
	_text = text;

	// エフェクトの模様を定義
	Rect tmp = _font(_text).regionAt(Scene::Center()).asRect();
	Rect region = Rect(Point(tmp.top().begin.asPoint().x, Scene::Center().y - 48), Point(tmp.w, 96));
	for (int i = 0; i < 3; i++)
		_quads.push_back(Quad(Point(0, 0), Point(-32, 0), Point(-32 - 64, 96), Point(0 - 64, 96)).movedBy(region.top().begin).movedBy(Point(-64 * i, 0)));
	for (int i = 0; i < 3; i++)
		_quads.push_back(Quad(Point(64, 0), Point(64 + 32, 0), Point(32, 96), Point(0, 96)).movedBy(region.top().end).movedBy(Point(64 * i, 0)));
}

void CompileEffect::update()
{
	// 32 / 256 = 8 フレームかけて透明から不透明にフェードイン
	if (_feed_in)
	{
		_color.setA(_color.a + 32);
		// フェードイン完了
		if (_color.a + 32 > 255)
			_feed_in = false;
	}
	// 60フレーム待つ
	else
		_wait -= 1;
	// 8 / 256 = 32 フレームかけて透明にフェードアウト
	if(_wait < 0)
		if(_color.a >= 0)
			_color.setA(_color.a - 8);
}

void CompileEffect::draw() const
{
	for(auto& quad:_quads)
		quad.draw(_color);
	_font(_text).drawAt(Scene::Center(), _color);
}

bool CompileEffect::finish()
{
	// 透明になったらエフェクト完了
	return (_color.a < 1);
}



SuccessEffect::SuccessEffect() : CompileEffect(U"SUCCESS", Palette::Lightgreen)
{
	// 文字と色を指定するだけ
}

FailureEffect::FailureEffect() : CompileEffect(U"FAILURE", Palette::Red)
{
	// 文字と色を指定するだけ
}
