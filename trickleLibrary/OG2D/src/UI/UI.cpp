#include "UI.h"

UI::UI() {}

UI::~UI() {}

//���W�A�t�@�C���p�X�A�摜������
void UI::Initialize(Vec2 pos, std::string path, int num, int life) {
	this->pos = pos;
	tex.TextureCreate(path);
	counter = 0;
	this->num = num;
	src = Box2D(0, 0, 256, 256);
	this->life = life;
}

void UI::Update() {
	counter++;
	if (counter % 30 == 0) {
		src.x += 256;
		src.w += 256;
		if (src.x >= 256 * num) {
			src.x = 0;
			src.w = 256;
		}
	}
}

void UI::Move(Vec2 pos) {
	this->pos = Vec2(pos.x - 20, pos.y - 140);
}

void UI::Render() {
	Box2D draw(pos.x, pos.y, 128.f, 128.f);
	draw.OffsetSize();
	tex.Draw(draw, src);
}

void UI::Finalize() {
	tex.Finalize();
}