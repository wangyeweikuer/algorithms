package org.wangye.autopdf.web;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 * 配置管理
 * @author wangye04 笨笨
 * @email wangye04@baidu.com
 * @datetime Sep 10, 2013 10:09:11 PM
 */
@Controller
@RequestMapping("/config")
public class ConfigController {
	
	/*@Autowired
	private ConfigRepo	configRepo;
	
	@RequestMapping(value = "/getByHost", method = RequestMethod.GET)
	@ResponseBody
	public String download(@RequestParam("host") String host) {
		return configRepo.getByHost(host);
	}*/
}
