'use strict';

var path = require( 'path' );

const CdrFlightAppsPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin' ) ).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join(__dirname, 'web'));
    
        var content = {
        	md: {
                shortDescription: 'Memory Dwell',
                longDescription: 'Memory Dwell.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main VM.',
                        filePath: 'main.lyt'
                    },
                    cdh: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Command and Data Handling',
                        longDescription: 'Command counters.',
                        filePath: 'cdh.pug'
                    },
                    stats: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Stats',
                        longDescription: 'MD Stats.',
                        filePath: 'stats.pug'
                    }
                }
        	}
        };
        
      	this.addContent(content);
    };
};
