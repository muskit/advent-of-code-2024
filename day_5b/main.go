package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	mapset "github.com/deckarep/golang-set/v2"
)


func main() {
	data, err := os.ReadFile("input.txt")
	// data, err := os.ReadFile("example.txt")
	if err != nil {
        panic(err)
    }
	dataStr := string(data)

	var sum int = 0
	rules := map[string]mapset.Set[string]{} 

	scanner := bufio.NewScanner(strings.NewReader(dataStr))
	scanner.Scan()
	line := scanner.Text()
	// rule building //
	for len(line) > 1 {
		// set rule
		token := strings.Split(line, "|")
		if rules[token[0]] == nil {
			rules[token[0]] = mapset.NewSet[string]()
		}
		rules[token[0]].Add(token[1])

		scanner.Scan()
		line = scanner.Text()
	}

	for k := range rules {
		fmt.Printf("%s: %s\n", k, rules[k])
	}

	// update analyzing //
	for scanner.Scan() {
		line = scanner.Text()
		println(line)

		visited := map[string]int{}
		tokens := strings.Split(line, ",")
		lineFixed := false

		for curIdx := 0; curIdx < len(tokens); curIdx++ {
			curPg := tokens[curIdx]
			// fmt.Printf("i=%d (%s) : %s\n", curIdx, curPg, strings.Join(tokens, ", "))

			if curIdx == 0 {
				visited[curPg] = curIdx
				continue
			}

			_, ruleExists := rules[curPg]
			if !ruleExists {
				fmt.Printf("no rule for %s\n", curPg)
				visited[curPg] = curIdx
				continue
			}

			ruleValues := rules[curPg].ToSlice()
			swapped := false
			for _, v := range ruleValues {
				if visitedIdx, found := visited[v]; found {
					badPg := v
					fmt.Printf("rule break: %s encountered after %s! swapping...\n", curPg, badPg)

					// swap tokens
					tokens[visitedIdx] = curPg
					tokens[curIdx] = badPg
					// reset visited
					for k := range visited {
						delete(visited, k)
					}
					
					swapped = true
					lineFixed = true
					break
				}
			}
			if swapped {
				curIdx = -1
			} else {
				visited[curPg] = curIdx
			}
		}

		if lineFixed {
			var midIdx = len(tokens)/2
			val, _ := strconv.Atoi(tokens[midIdx])
			sum += val
		}
		println(strings.Join(tokens, ","))
		println()
	}

	fmt.Printf("sum: %d\n", sum)
	println("answer > 6016") // sum changes on every run
}