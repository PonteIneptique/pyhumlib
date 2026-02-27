from setuptools import setup, Extension
import pybind11
import glob

humlib_sources = glob.glob("humlib/src/*.cpp")

# Add pugixml cpp
humlib_sources += ["vendor/pugixml/src/pugixml.cpp"]

ext_modules = [
    Extension(
        "pyhumlib",
        sources=humlib_sources + ["bindings.cpp"],

        include_dirs=[
            pybind11.get_include(),
            "humlib/include",   # ✅ headers
            "humlib/src",       # sometimes needed
            "vendor/pugixml/src",
        ],

        language="c++",
        extra_compile_args=["-std=c++17"],
    )
]

setup(
    name="pyhumlib",
    version="0.0.1",
    ext_modules=ext_modules,
    description="Python bindings for humlib with XML export",
    zip_safe=False,
)