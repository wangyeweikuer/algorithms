package org.wangye.autopdf.repo;

import org.springframework.stereotype.Repository;

/**
 * TODO 请注释： 
 * @author wangye04 笨笨
 * @email wangye04@baidu.com
 * @datetime Sep 10, 2013 10:12:51 PM
 */
@Repository
public class ConfigRepo {
	
	/*private final Map<String, String>	maps	= new HashMap<String, String>();
	
	@PostConstruct
	public void init() throws IOException {
		// Enumeration<URL> fs = Thread.currentThread().getContextClassLoader().getResources("conf/*");
		PathMatchingResourcePatternResolver resolver = new PathMatchingResourcePatternResolver();
		Resource[] fs = resolver.getResources("classpath:conf/**");
		for (Resource r : fs) {
			File f = r.getFile();
			String k = f.getName();
			String v = FileUtils.readFileToString(f);
			maps.put(k, v);
		}
	}
	
	public String getByHost(String host) {
		return maps.get(host);
	}*/
}
