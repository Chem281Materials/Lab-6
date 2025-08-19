from setuptools import setup, Extension
from Cython.Build import cythonize

ext_modules = [
    Extension(
        name="clash",
        sources=["src/cython/clash.pyx", "src/clashes.cpp"],
        language="c++",
        include_dirs=["include", "/usr/include/openbabel3"],
        libraries=["openbabel"],
        library_dirs=["/usr/lib"],
        extra_compile_args=["-std=c++11"],
    )
]

setup(
    name="clash",
    packages=["clash"],
    ext_modules=cythonize(ext_modules, language_level=3),
    zip_safe=False,
)
