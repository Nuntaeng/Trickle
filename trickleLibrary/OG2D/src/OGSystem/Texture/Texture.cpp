#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//--------------------------------------------------
//@:Textureclass									
//--------------------------------------------------
void Texture::TextureCreate(std::string path)
{
	GLuint id;
	this->TextureID = 1;
	//�e�N�X�`�����T�C�Y��������������
	glGenTextures(this->TextureID, &id);
	//�e�N�X�`�����o�C���h����
	glBindTexture(GL_TEXTURE_2D, id);
	//�摜��ǂݍ���
	int width;
	int height;
	int comp;
	std::string filepath = FileName + path;
	//�摜�f�[�^��ǂݍ���
	unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &comp, 0);
	//�f�[�^�`����I��
	GLint type = (comp == 3) ? GL_RGB : GL_RGBA;
	//�摜�f�[�^��OpenGL�֑���
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
	TextureSize = Vec2(width, height);
	//���f�[�^�̔j��
	stbi_image_free(data);
	//�\���p�ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	this->_TexId = id;
	_materix[0] = { 0,0 };
	_materix[1] = { width,0 };
	_materix[2] = { width,height };
	_materix[3] = { 0,height };
	angle = 0.f;
}
Texture::Texture()
{

}
void Texture::Draw(Box2D draw, Box2D src) {
	//���W
	GLfloat vtx[] = {
		draw.x,draw.h,
		draw.w,draw.h,
		draw.w,draw.y,
		draw.x,draw.y,
	};
	_Rotate(angle, &vtx[0]);
	glVertexPointer(2, GL_FLOAT, 0, vtx);
	//�摜���W
	const GLfloat texuv[] = {
		src.x / TextureSize.x,src.h / TextureSize.y,
		src.w / TextureSize.x,src.h / TextureSize.y,
		src.w / TextureSize.x,src.y / TextureSize.y,
		src.x / TextureSize.x,src.y / TextureSize.y,
	};
	//0.1�ȉ��̃J���[��\�����Ȃ��A����œ��߂���Ă镔����؂蔲�����Ƃœ��߂��ꂽ�摜�ɂȂ�
	glAlphaFunc(GL_GREATER, (GLclampf)0.1);
	glTexCoordPointer(2, GL_FLOAT, 0, texuv);
	//OpenGL�ɓo�^����Ă���e�N�X�`����R�Â�
	glBindTexture(GL_TEXTURE_2D, _TexId);
	//�`��
	//glMatrixMode(GL_TEXTURE);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}
void Texture::Finalize()
{
	glDeleteTextures(1, &this->_TexId);
}
void Texture::Rotate(float radian)
{
	this->angle = radian;
}
void Texture::_Rotate(float radian, GLfloat *_mate)
{
	//���W�A���̒l�ɕύX
	float tora = OG::ToRadian(radian);
	//���_���w��
	Vec2 Center((*(_mate + 2) + *(_mate)) / 2, (*(_mate + 5) + *(_mate + 1)) / 2);
	//��]���̌��_�̒l�𓱂�
	GLfloat v[]
	{
		*(_mate)-Center.x,*(_mate + 1) - Center.y,
		*(_mate + 2) - Center.x,*(_mate + 3) - Center.y,
		*(_mate + 4) - Center.x,*(_mate + 5) - Center.y,
		*(_mate + 6) - Center.x,*(_mate + 7) - Center.y,
	};
	//��]�s��̐���
	GLfloat ma[4] = {
		cosf(tora),-sinf(tora),
		sinf(tora),cosf(tora),
	};
	//��]�s��̌v�Z
	*(_mate) = (v[0] * ma[0]) + (v[1] * ma[1]);
	*(_mate + 1) = (v[0] * ma[2]) + (v[1] * ma[3]);

	*(_mate + 2) = (v[2] * ma[0]) + (v[3] * ma[1]);
	*(_mate + 3) = (v[2] * ma[2]) + (v[3] * ma[3]);

	*(_mate + 4) = (v[4] * ma[0]) + (v[5] * ma[1]);
	*(_mate + 5) = (v[4] * ma[2]) + (v[5] * ma[3]);

	*(_mate + 6) = (v[6] * ma[0]) + (v[7] * ma[1]);
	*(_mate + 7) = (v[6] * ma[2]) + (v[7] * ma[3]);

	//��]���̌��_�̈ړ������������ɖ߂�
	*(_mate) = *(_mate)+Center.x;
	*(_mate + 1) = *(_mate + 1) + Center.y;

	*(_mate + 2) = *(_mate + 2) + Center.x;
	*(_mate + 3) = *(_mate + 3) + Center.y;

	*(_mate + 4) = *(_mate + 4) + Center.x;
	*(_mate + 5) = *(_mate + 5) + Center.y;

	*(_mate + 6) = *(_mate + 6) + Center.x;
	*(_mate + 7) = *(_mate + 7) + Center.y;
}
Texture::~Texture()
{
	glDeleteTextures(1, &this->_TexId);
}