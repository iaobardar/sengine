typedef float mat4[4 * 4];
typedef float vec4[4];

void mat4mult(mat4 a, mat4 b, mat4 out)
{
	for (int c = 0; c < 4; ++c)
		for (int r = 0; r < 4; ++r)
		{
			out[r + 4 * c] = 0;
			for (int i = 0; i < 4; ++i)
				out[r + 4 * c] += a[r + 4 * i] * b[i + 4 * c];
		}
}

void mat4copy(mat4 origin, mat4 target)
{
	for (int i = 0; i < 16; ++i)
		target[i] = origin[i];
}

void mat4print(mat4 in)
{
	for (int r = 0; r < 16; r+=4)
		printf("%2.2f, %2.2f, %2.2f, %2.2f\n", in[r], in[r + 1], in[r + 2], in[r + 3]);
}

void vec4print(vec4 in)
{
	printf("%2.2f, %2.2f, %2.2f, %2.2f\n", in[0], in[1], in[2], in[3]);
}

void mat4translate(mat4 a, float x, float y, float z)
{
	mat4 transform = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1,
	};

	mat4 output;

	mat4mult(a, transform, output);

	mat4copy(output, a);
}