#include <stdio.h>
#include <assert.h>
#include "sshader.h"

void debug_log(char* msg)
{
	printf("\033[32m%s\033[0m\n", msg);
}

shaderlistfile load_shader_file(char* filename)
{
	debug_log("loading shaders");
	debug_log(filename);

	sstring file_src;
	file_src.length = read_whole_file(filename, (void**)&file_src.data);
	assert(file_src.length > 0);
	//putss(&file_src);
	shaderlistfile slf = {
		.src = file_src,
		.count = 0
	};

	printf("%zi\n", file_src.length);

	sstring shader_sep = sv_cstr("#--");

	size_t shader_start = 0;
	while (shader_start < file_src.length - 1)
	{
		size_t next_start = ssfind(&shader_sep, &file_src, shader_start);
		printf("%zi\n", next_start);
		slf.shaders[slf.count++] = sv_ss(&file_src, shader_start, next_start - shader_start);
		printf("\033[32mShader\033[0m %zi -> %zi\n", shader_start, next_start);
		//putss(&slf.shaders[slf.count - 1]);
		shader_start = next_start + shader_sep.length;
	}

	for (size_t i = 0; i < slf.count; ++i)
	{
		printf("\033[32mShader\033[0m %zi\n", i);
		putss(&slf.shaders[i]);
	}

	return slf;
}

GLuint init_shader(GLuint type, sstring* src)
{
	debug_log("compiling shader:");
	putss(src);

	const GLsizei msg_size =  512;
	GLchar message[msg_size];
	GLint compile_worked;

	GLuint shader = glCreateShader(type);

	GLint len = src->length;
	assert(len == src->length);
	glShaderSource(shader, 1, (const char *const *)&src->data, &len);
	glCompileShader(shader);

	// Debug
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_worked);
	if (!compile_worked)
	{
		glGetShaderInfoLog(shader, msg_size, NULL, message);
		puts(message);
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}


GLuint init_shader_program(sstring* vert_src, sstring* frag_src)
{
	GLuint vshader = init_shader(GL_VERTEX_SHADER, vert_src);
	GLuint fshader = init_shader(GL_FRAGMENT_SHADER, frag_src);

	if (!vshader || !fshader) return 0;

	GLuint program = glCreateProgram();
	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	glLinkProgram(program);

	// Debug
	const GLsizei msg_size =  512;
	GLchar message[msg_size];
	GLint link_worked;

	glGetProgramiv(program, GL_LINK_STATUS, &link_worked);
	if (!link_worked)
	{
		glGetProgramInfoLog(program, msg_size, NULL, message);
		puts(message);
		glDeleteProgram(program);
		return 0;
	}

	return program;
}
