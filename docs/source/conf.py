#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Hikyuu documentation build configuration file, created by
# sphinx-quickstart on Tue Mar 29 22:24:37 2016.
#
# This file is execfile()d with the current directory set to its
# containing dir.
#
# Note that not all possible configuration values are present in this
# autogenerated file.
#
# All configuration values have a default; values that are commented out
# serve to show the default.

from recommonmark.parser import CommonMarkParser
import sphinx_rtd_theme
import sys
import os

sys.path.insert(0, os.path.abspath('.'))

version = '2.1.5'
release = version

# General information about the project.
project = 'Hikyuu Quant Framework'
copyright = '2017, fasiondog，<a href="https://hikyuu.org/">Hikyuu</a>'
author = 'fasiondog'

extensions = [
    'recommonmark',
    'sphinx_markdown_tables',
    'sphinx.ext.autosectionlabel',
    'sphinx.ext.mathjax'
]
autosectionlabel_prefix_document = True

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
# source_suffix = ['.rst', '.md']
source_suffix = '.rst'

# The encoding of source files.
# source_encoding = 'utf-8-sig'

# The master toctree document.
master_doc = 'index'
language = 'zh_CN'
exclude_patterns = []
pygments_style = 'sphinx'
todo_include_todos = False

html_theme = 'sphinx_rtd_theme'
html_favicon = "./_static/favicon.ico"

html_static_path = ['_static']
html_css_files = [
    'style.css',
]


html_use_index = True
html_search_language = 'zh'
htmlhelp_basename = 'Hikyuudoc'

source_parsers = {
    '.md': CommonMarkParser,
}
source_suffix = ['.rst', '.md']

needs_sphinx = '4.2.0'
