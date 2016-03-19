#!/usr/bin/env python2.7.6
# -*- coding: utf-8 -*-

import socket

hostname = 'baidu.com'
addr = socket.gethostbyname(hostname)
print 'the address of', hostname, 'is', addr
