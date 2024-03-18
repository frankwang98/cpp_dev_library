#!/usr/bin/env bash
# 制作pip包： https://www.cnblogs.com/sting2me/p/6550897.html
# 发布pip包： https://packaging.python.org/tutorials/packaging-projects/
rm -rf dist/*
python setup.py sdist # 生成源分发包，需要setup.sh
python setup.py bdist_wheel --universal # 构建一个 Python 项目的 wheel 分发包，二进制包