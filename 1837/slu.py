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

class Graph:
    def __init__(self, directed = False, graph = None):
        self.__directed = directed
        if graph is None:
            self.__graph = {}
        else:
            self.__graph = graph

    def get_vertexs(self):
        return self.__graph.keys()


    def get_edges(self):
        def __generate_edges(graph):
            edges = []
            for v in graph.keys():
                for n in graph[v]:
                    if {n, v} not in edges:
                        edges.append({v, n})
            return edges
        return __generate_edges(self.__graph)


    def add_vertex(self, v):
        ''' 
        Add a vertex to graph
        @param v vertex to be added
        @return nothing 
        '''
        if v not in self.__graph.keys():
            self.__graph[v] = []


    def add_edge(self, begin, end):
        '''
        Add an edge to graph
        @param begin begin vertex of the edge
        @param end end vertex of the edge
        @return nothing
        '''

        def _add_edge(g, b, e):
            if b in g.keys():
                if e not in g[b]:
                    g[b].append(e)
            else:
                g[b] = [e]

        
        _add_edge(self.__graph, begin, end)
        if not self.__directed:
            _add_edge(self.__graph, end, begin)


    def find_all_paths(self, begin, end):
        '''
        Find all paths from begin to end
        @param begin begin vertex of the path
        @param end end vertex of the path
        @return None if no path, list of all paths otherwise
        '''

        def _find_all_paths(graph, begin, end, path = []):
            path = path + [begin]
            if begin not in graph.keys():
                return []
            if begin == end:
                return [path]

            paths = []
            for vertex in graph[begin]:
                if vertex not in path:
                    newpaths = _find_all_paths(graph, vertex, end, path)
                    for newpath in newpaths:
                        paths.append(newpath)
            return paths

        return _find_all_paths(self.__graph, begin, end)


    def find_shortest_path(self, begin, end):
        '''
        Find the shortest path from begin to end
        @param begin begin vertex of the path
        @param end end vertex of the path
        @return None if no path found, shortest path otherwise
        '''
        paths = self.find_all_paths(begin, end)
        shortest = None
        for path in paths:
            if shortest is None:
                shortest = path
            else:
                if len(path) < len(shortest):
                    shortest = path

        return shortest


def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')


def get_int_from_stdin():
    return int(get_str_from_stdin())


def get_input():
    n = 0
    i = 0
    g = Graph()
    for line in sys.stdin:
        if n == 0:
            n = int(line.strip('\r\n'))
            if (n <= 0):
                break;
            else:
                continue        

        names = line.strip('\r\n').split(' ')
        assert len(names) == 3
        g.add_edge(names[0], names[1])
        g.add_edge(names[0], names[2])
        g.add_edge(names[1], names[2])
        
        i = i + 1
        if i >= n:
            break;        

    return g


def calc(champion, graph):
    r = {}
    for v in graph.get_vertexs():
        path = graph.find_shortest_path(champion, v)
        if path is None:
            r[v] = 'undefined'
        else:
            r[v] = len(path) - 1
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
        print('{0} {1}'.format(n, result[n]), end=e)
        i = i + 1

if __name__ == '__main__':
    graph = get_input()
    result = calc('Isenbaev', graph)
    show_result(result)
