#include "Time.h"
#include "Direct3D.h"

void Time::TimeDraw(int x, int y)
{
	if (Direct3D::GetStatus() == 0)
	{
		//true�Ȃ�
		if (Timeflag_)
		{
			time_ += 000.016; //60Fps������񖈃t���[��0.016
			char buf[12];
			snprintf(buf, 12, "Time:%.2f", time_);

			//�l��\��
			text_->Draw(x, y, buf,3);
		}
		else
		{
			//false�Ȃ炱���\��
			text_->Draw(x, y, "Time:0.00",3);
		}
	}
}
