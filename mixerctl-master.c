#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/audioio.h>
#include <sys/limits.h>

#include <err.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

__dead void usage(void);

int
main(int argc, char *argv[])
{
	char	*arg;
	char	 sign;
	int	 diff;
	int	 mixer_fd;
	int	 rc;
	struct	 mixer_devinfo devinfo;
	struct	 mixer_ctrl ctrl;
	int	 num_channels;
	u_char	*level;
	int	 i;

	if (argc != 2)
		usage();

	arg = argv[1];

	if (strlen(arg) <= 1)
		usage();

	sign = arg[0];
	if (sign != '+' && sign != '-')
		usage();

	diff = atoi(arg);
	if (diff == 0)
		exit(0);

	diff = (int)round(((double) diff / 100.0) * (double)UCHAR_MAX);

	mixer_fd = open("/dev/mixer", O_RDONLY);
	if (mixer_fd == -1)
		err(1, NULL);

	devinfo.index = 0;
	while ((rc = ioctl(mixer_fd, AUDIO_MIXER_DEVINFO, &devinfo)) != -1) {
		if (strcmp(devinfo.label.name, AudioNmaster) == 0)
			break;
		devinfo.index++;
	}

	if (rc == -1)
		err(1, NULL);

	ctrl.dev = devinfo.index;
	if (ioctl(mixer_fd, AUDIO_MIXER_READ, &ctrl) == -1)
		err(1, NULL);

	if (ctrl.type != AUDIO_MIXER_VALUE)
		errx(1, "Unable to read master device value");

	num_channels = ctrl.un.value.num_channels;
	level = ctrl.un.value.level;
	for (i = 0; i < num_channels; i++) {
		int volume = level[i] + diff;

		if (volume < 0)
			volume = 0;
		else if (UCHAR_MAX < volume)
			volume = UCHAR_MAX;

		level[i] = volume;
	}

	if (ioctl(mixer_fd, AUDIO_MIXER_WRITE, &ctrl) == -1)
		err(1, NULL);

	(void)close(mixer_fd);

	return 0;
}

__dead void
usage(void)
{
	extern char *__progname;	/* from crt0.o */
	fprintf(stderr, "usage: %s [+%%|-%%]\n", __progname);
	exit(1);
}
