package org.wangye.web;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 * TODO 请注释：
 * @author wangye04 笨笨
 * @email wangye04@baidu.com
 * @datetime Dec 26, 2013 10:54:44 PM
 */
@Controller
public class IndexController {
	
	@RequestMapping(value = {"", "/", "/index"})
	public String index() {
		return "index";
	}
}
