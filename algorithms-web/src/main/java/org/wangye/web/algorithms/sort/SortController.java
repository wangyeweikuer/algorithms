package org.wangye.web.algorithms.sort;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

/**
 * @author wangye04 笨笨
 * @email wangye04@baidu.com
 * @datetime Dec 26, 2013 10:24:14 PM
 */
@Controller
@RequestMapping("/sort")
public class SortController {
	
	@RequestMapping("random")
	public String randomList(Model model,@RequestParam(defaultValue = "20", required = false) int number) {
		List<Integer> results = new ArrayList<Integer>();
		int c = number;
		while(c > 0){
			Random r = new Random();
			int v = r.nextInt(number);
			if(!results.contains(v)){
				results.add(v);
				c--;
			}
		}
		model.addAttribute("numbers", results);
		return "sort/randomCards";
	}
	
	@RequestMapping("sort")
	@ResponseBody
	public List<Object> sort(@RequestParam List<Integer> arrays, @RequestParam SortType type) {
		return null;
	}
}
