

#include "uid.h"

int main()
{
	ilrd_uid_t uid_1 = UIDCreate();
	ilrd_uid_t uid_2 = UIDCreate();

	UIDIsSame(uid_1, uid_2);

	

	return (1);
}
