#pragma once
class CompileEffect
{
protected:
	bool _feed_in;
	Array<Quad> _quads;
	Color _color;
	Font _font;
	int _wait;
	String _text;
public:
	CompileEffect() {};
	CompileEffect(String text, Color color);

	void update();
	void draw() const;

	// エフェクト完了判定
	bool finish();
};


// 成功時（Success）のエフェクト
class SuccessEffect : public CompileEffect
{
public:
	SuccessEffect();
};


// 失敗時（Failure）のエフェクト
class FailureEffect : public CompileEffect
{
public:
	FailureEffect();
};
