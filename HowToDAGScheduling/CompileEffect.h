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

	bool finish() { return (_color.a - 2 < 1); };
};

class SuccessEffect : public CompileEffect
{
public:
	SuccessEffect();
};

class FailureEffect : public CompileEffect
{
public:
	FailureEffect();
};
