package = 'SIMD'
version = '0.1-1'
source = {
	url = 'git://github.com/iskolbin/lsimd',
	tag = 'v1.0',
}
description = {
	summary = 'Lua bindings to SIMD',
	detailed = [[]],
	homepage = 'https://github.com/iskolbin/lsimd',
	license = 'MIT/X11',
}
dependencies = {
	'lua >= 5.1'
}
build = {
	type = 'builtin',
	modules = {
		simd = {
			sources = {
				'simd.c',
			},
		}
	}
}
