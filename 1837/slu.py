#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1837. Isenbaev's Number
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
Vladislav Isenbaev is a two-time champion of Ural, vice champion of TopCoder
Open 2009, and absolute champion of ACM ICPC 2009. In the time you will spend
reading this problem statement Vladislav would have solved a problem. Maybe,
even two…
Since Vladislav Isenbaev graduated from the Specialized Educational and
Scientific Center at Ural State University, many of the former and present
contestants at USU have known him for quite a few years. Some of them are proud
to say that they either played in the same team with him or played in the same
team with one of his teammates…
Let us define Isenbaev's number as follows. This number for Vladislav himself
is 0. For people who played in the same team with him, the number is 1. For
people who weren't his teammates but played in the same team with one or more
of his teammates, the number is 2, and so on. Your task is to automate the
process of calculating Isenbaev's numbers so that each contestant at USU would
know their proximity to the ACM ICPC champion.

[Input]
The first line contains the number of teams n (1 ≤ n ≤ 100). In each of the
following n lines you are given the names of the three members of the corres-
ponding team. The names are separated with a space. Each name is a nonempty
line consisting of English letters, and its length is at most 20 symbols. The
first letter of a name is capital and the other letters are lowercase.

[Output]
For each contestant mentioned in the input data output a line with their name
and Isenbaev's number. If the number is undefined, output “undefined” instead
of it. The contestants must be ordered lexicographically.
'''

from __future__ import print_function
import sys;
import math;


class Node:
    WHITE = 0
    GREY = 1
    BLACK = 2
    
    def __init__(self, vertex):
        self.__vertex = vertex
        self.__color = Node.WHITE
        self.__distance = -1
        self.__parent = None
        
    def __repr__(self):
        #return "v: {0}, c: {1}, d: {2}, p: {3}".format(repr(self.__vertex), self.__color, self.__distance, self.__parent)
        return repr(self.__vertex)
        
    def get_vertex(self):
        return self.__vertex
        
    def set_color(self, color):
        self.__color = color
        
    def get_color(self):
        return self.__color
    
    def set_distance(self, d):
        self.__distance = d

    def get_distance(self):
        return self.__distance
    
    def set_parent(self, p):
        self.__parent = p
        
    def get_parent(self):
        return self.__parent


class UndirectedGraph:
    '''
    Undirected graph represented in adjacent list
    '''
    
    def __init__(self, graph = None):
        if graph is None:
            self.__graph = {}
        else:
            self.__graph = graph
            
    def __repr__(self):
        return repr(self.__graph)
            
    
    def get_vertexs(self):
        return self.__graph.keys()


    def add_vertex(self, v):
        ''' 
        Add a vertex to graph
        @param v vertex to be added
        @return nothing 
        '''
        
        node = None
        for k in self.__graph.keys():
            if k.get_vertex() == v:
                node = k
                break
            
        if node is None:
            node = Node(v)
            self.__graph[node] = []
            
        return node


    def add_edge(self, x, y):
        '''
        Add an edge to graph
        @param x one vertex of the edge
        @param y another vertex of the edge
        @return nothing
        '''

        node_x = self.add_vertex(x)
        node_y = self.add_vertex(y)
        self.__graph[node_x].append(node_y)
        self.__graph[node_y].append(node_x)


    def __reset_nodes(self, x):
        node = None
        for k in self.__graph.keys():
            if (k.get_vertex() == x):
                k.set_color(Node.GREY)
                k.set_distance(0)
                node = k
            else:
                k.set_color(Node.WHITE)
                k.set_distance(-1)
            k.set_parent(None)
        return node


    def bfs(self, x):
        '''
        Breadth First Search
        @param x source vertex
        @return BFS tree
        '''
        node = self.__reset_nodes(x)
        queue = [node]
        while len(queue) > 0:
            u = queue.pop(0)
            for v in self.__graph[u]:
                if v.get_color() == Node.WHITE:
                    v.set_color(Node.GREY)
                    v.set_distance(u.get_distance() + 1)
                    v.set_parent(u)
                    queue.append(v)
            u.set_color(Node.BLACK)


def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')


def get_int_from_stdin():
    return int(get_str_from_stdin())


def get_input():
    n = 0
    i = 0
    g = UndirectedGraph()
    for line in sys.stdin:
        if n == 0:
            n = int(line.strip('\r\n'))
            if (n <= 0):
                break
            else:
                continue        

        names = line.strip('\r\n').split(' ')
        l = len(names)
        for u in range(l - 1):
            for v in range(u + 1, l):
                #print("adding edge: {0}, {1}".format(names[u], names[v]))
                g.add_edge(names[u], names[v])
        
        i = i + 1
        if i >= n:
            break
        
    #print(g)

    return g


def calc(champion, graph):
    r = {}
    graph.bfs(champion)
    for v in graph.get_vertexs():
        d = v.get_distance()
        n = v.get_vertex()
        if d == -1:
            r[n] = "undefined"
        else:
            r[n] = d
        
    return r


def show_result(result):
    names = result.keys()
    names.sort()
    l = len(result)
    i = 1
    for n in names:
        e = None
        if i == l:
            e = ''
        else:
            e = '\n'
        print('{0} {1}'.format(n, result[n]), end = e)
        i = i + 1

if __name__ == '__main__':
    graph = get_input()
    result = calc('Isenbaev', graph)
    show_result(result)
