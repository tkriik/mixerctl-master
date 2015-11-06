#include <sys/types.h>
#include <sys/audioio.h>
#include <sys/ioctl.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(void)
{
	int mixer_fd = open("/dev/mixer", O_RDONLY);
	if (mixer_fd == -1) {
		fprintf(stderr, "Unable open mixer device. Exiting...\n");
		exit(1);
	}

	struct mixer_devinfo devinfo;
	devinfo.index = 0;
	while (ioctl(mixer_fd, AUDIO_MIXER_DEVINFO, &devinfo) != -1) {		
		puts(devinfo.label.name);
		devinfo.index++;
	}

	(void)close(mixer_fd);

	return 0;
}
