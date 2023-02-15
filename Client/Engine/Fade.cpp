#include "Fade.h"

void Fade::FadeIn(int handle, float ratio)
{
	float strong = Image::GetAlpha(handle);
	strong += 1 * ratio;

	//�A���t�@�l���������Ⴄ��
	if (strong < 255)
		Image::SetAlpha(handle, strong);
}

void Fade::FadeOut(int handle, float ratio)
{
	float strong = Image::GetAlpha(handle);
	strong -= 1 * ratio;

	//�A���t�@�l���������Ⴄ��
	if (strong > 0)
		Image::SetAlpha(handle, strong);

}

void Fade::FadeInOut(int handle, float ratio)
{

	strong2 += 3 * ratio * move2;

	//�A���t�@�l���������Ⴄ��
	if (strong2 >= 255)
		move2 *= -1;

	if (strong2 <= 0)
		move2 *= -1;

	Image::SetAlpha(handle, strong2);

}


