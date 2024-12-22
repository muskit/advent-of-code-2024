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

		visited := mapset.NewSet[string]()
		valid := true
		// check update line
		tokens := strings.Split(line, ",")
		for i, curPg := range tokens {
			if i == 0 {
				visited.Add(curPg)
				continue
			}

			_, ruleExists := rules[curPg]
			if !ruleExists {
				fmt.Printf("no rule for %s\n", curPg)
				visited.Add(curPg)
				continue
			}

			outOfOrder := false
			badPg := ""
			ruleValues := rules[curPg].ToSlice()
			for _, v := range ruleValues {
				if visited.Contains(v) {
					outOfOrder = true
					badPg = v
					break
				}
			}
			if outOfOrder {
				fmt.Printf("rule break: %s encountered before %s!\n", badPg, curPg)
				valid = false
				break
			}
			visited.Add(curPg)
		}
		if valid {
			var midIdx = len(tokens)/2
			val, _ := strconv.Atoi(tokens[midIdx])
			sum += val
		}
		notStr := "GOOD"
		if !valid {
			notStr = "BAD!"
		}
		fmt.Printf("%s : %s\n\n", notStr, line)
	}
	fmt.Printf("sum: %d\n", sum)
	println("answer < 5873") // used the visited set wrongly!!!
}