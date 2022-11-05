from setuptools import setup, Extension

base = Extension("graphicx", sources=["src/graphicx.c"])

setup(
    name="graphicx",
    version = "1.0",
    description="For now, just a test",
    ext_modules = [base]
)